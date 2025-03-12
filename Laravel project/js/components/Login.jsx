import React, {useState} from 'react'
import Router from '../router/index';
import {NavLink} from 'react-router-dom';
import { useNavigate } from 'react-router-dom';
import { AiOutlineEye, AiOutlineEyeInvisible } from 'react-icons/ai';


export const Login = (props) => {
  const [getEmail, setEmail] = useState('');
  const [getPass, setPass] = useState('');
  const [type, setType] = useState("password");


 

const handleLogin = async (e) => {
  e.preventDefault();

  const response = await fetch("http://127.0.0.1:8000/api/login", {
    method: "POST",
    headers: { 
      "Content-Type": "application/json", 
      "Accept": "application/json",
    },
    body: JSON.stringify({
      email: getEmail,
      password: getPass
    }),
  });

  const data = await response.json();
  console.log(data);
  if (response.ok) {
    if (data.access_token) {
      localStorage.setItem("access_token", data.access_token);
    }
    alert("Login successful!");
    navigate("/profile")
  } else {
    alert("Invalid credentials!");
  }
};

  const navigate = useNavigate();

  return (

    <div className="App">
      <div className="container">
          <form className="loginScreen" 
          onSubmit={handleLogin}>
              <label className="loginLabel"><b>Login</b></label>
              <label htmlFor="email">Email</label>
              <input value={getEmail} onChange={(e) => setEmail(e.target.value)} type="email" placeholder="youremail@gmail.com" id="email" name="email"/>
              <label htmlFor="password">Password</label>
              <div className="input-with-icon-div">
                <input className="iconInput" value={getPass} onChange={(e) => setPass(e.target.value)} type={type} placeholder="********" id="password" name="password"/>
                <span className="icon-span" onClick={() => setType(type === "password" ? "text" : "password")}>
                  {type === "password" ? <AiOutlineEyeInvisible size={22} /> : <AiOutlineEye size={22} />}
                </span>
              </div>
              <button className="submitButton" type="submit">Log In</button>
          </form>
          <NavLink to="/register" className="loginButton">
            Register new account
          </NavLink>
          <button className="forgotButton" >Forgot Password</button>
      </div>
    </div>
  )
};


