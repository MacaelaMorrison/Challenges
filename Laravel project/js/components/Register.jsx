import React, { useState } from 'react';
import Router from '../router/index';
import {NavLink} from 'react-router-dom';
import { AiOutlineEye, AiOutlineEyeInvisible } from 'react-icons/ai';
import { BsCheckCircle, BsXCircle } from 'react-icons/bs';
import { useNavigate } from 'react-router-dom';

export const Register = (props) => {
  const [getEmail, setEmail] = useState("");
  const [getPass, setPass] = useState("");
  const [getPass2, setPass2] = useState("");
  const [getName, setName] = useState("");

  // Strong password states
  const [type, setType] = useState("password");
  const [lowerValidated, setLowerValidated] = useState(false);
  const [upperValidated, setUpperValidated] = useState(false);
  const [numberValidated, setNumberValidated] = useState(false);
  const [specialValidated, setSpecialValidated] = useState(false);
  const [lengthValidated, setLengthValidated] = useState(false);
  const [show, toggleShow] = useState(false);

  const handleInputFocus = () => toggleShow(true);
  const handleInputBlur = () => toggleShow(false);

  const handleChange = (value) => {
    setLowerValidated(/(?=.*[a-z])/.test(value));
    setUpperValidated(/(?=.*[A-Z])/.test(value));
    setNumberValidated(/(?=.*[0-9])/.test(value));
    setSpecialValidated(/(?=.*[!@#$%^&*])/.test(value));
    setLengthValidated(/(?=.{8,})/.test(value));
  };
  
  const navigate = useNavigate();
  
  const handleRegister = async (e) => {
    e.preventDefault();

    if (getPass !== getPass2) {
      alert("Passwords do not match!");
      return;
    }

    const response = await fetch("http://127.0.0.1:8000/api/register", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        name: getName,
        email: getEmail,
        password: getPass
      }),
    });

    const data = await response.json();
    console.log(data);
    if (response.ok) {
      alert("User registered successfully!");
      navigate("/");
    } else {
      alert("Error: " + JSON.stringify(data));
    }
  };

  return (
    <div className="App">
      <div className="container">
        <form className="registerScreen" onSubmit={handleRegister}>
          <label className="registerLabel"><b>Register New Account</b></label>
          <label htmlFor="name">Full Name</label>
          <input value={getName} name="name" id="name" onChange={(e) => setName(e.target.value)} placeholder='FirstName LastName'/>
          <label htmlFor="email">Email</label>
          <input value={getEmail} onChange={(e) => setEmail(e.target.value)} type="email" placeholder="youremail@gmail.com" id="email" name="email"/>
          <label htmlFor="password">Password</label>
          <div className='input-with-icon-div form-control'>
            <input className='iconInput' value={getPass} onChange={(e) => setPass(e.target.value)} type={type} placeholder="********" id="password" name="password"
            onInput={(e)=>handleChange(e.target.value)} onFocus={handleInputFocus} onBlur={handleInputBlur}/>
            <span className='icon-span' onClick={() => setType(type === "password" ? "text" : "password")}>
              {type === "password" ? <AiOutlineEyeInvisible size={22} /> : <AiOutlineEye size={22} />}
            </span>
          </div>
          {show && 
            <main className='requirements-box'> 
              {[{
                validated: lowerValidated, text: "At least one lowercase letter"
              }, {
                validated: upperValidated, text: "At least one uppercase letter"
              }, {
                validated: numberValidated, text: "At least one number"
              }, {
                validated: specialValidated, text: "At least one special character"
              }, {
                validated: lengthValidated, text: "At least 8 characters long"
              }].map((req, idx) => (
                <div key={idx} className={req.validated ? "validated" : "not-validated"}>
                  <span className={`reqIcon ${req.validated ? "green" : ""}`}>
                    {req.validated ? <BsCheckCircle /> : <BsXCircle />}
                  </span>
                  {req.text}
                </div>
              ))}
            </main>
          }
          
          <label htmlFor="confirm_password">Confirm password</label>
          <input value={getPass2} onChange={(e) => setPass2(e.target.value)} type="password" placeholder="********" id="confirm_password" name="confirm_password"/>
          <button className="submitButton" type="submit">Register</button>
        </form>
        <NavLink to="/" className="loginButton">
          Login instead
        </NavLink>
      </div>
    </div>
  );
};
