import React, { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';

export const Profile = () => {
  const navigate = useNavigate();
  const [profile, setProfile] = useState(null);
  const [editEmail, setEditEmail] = useState(false);
  const [editPassword, setEditPassword] = useState(false);
  const [newEmail, setNewEmail] = useState('');
  const [newPassword, setNewPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');

  // Fetch profile data on component mount
  useEffect(() => {
    const token = localStorage.getItem("access_token"); // Retrieve token from storage
    fetch("http://127.0.0.1:8000/api/profile", {
      headers: {
        "Content-Type": "application/json",
        "Accept": "application/json",
        "Authorization": "Bearer " + token,
      },
    })
      .then(response => {
        if (response.ok) return response.json();
        else throw new Error("Unauthorized");
      })
      .then(data => setProfile(data))
      .catch(error => {
        console.error("Error fetching profile:", error);
        navigate("/login"); // Redirect if not authenticated
      });
  }, [navigate]);

  // Update email in the backend
  const handleEmailUpdate = async () => {
    const token = localStorage.getItem("access_token");
    const response = await fetch("http://127.0.0.1:8000/api/profile/email", {
      method: "PUT",
      headers: { 
        "Content-Type": "application/json",
        "Accept": "application/json",
        "Authorization": "Bearer " + token,
      },
      body: JSON.stringify({ email: newEmail }),
    });
    const data = await response.json();
    if (response.ok) {
      alert("Email updated successfully!");
      setProfile({ ...profile, email: newEmail });
      setEditEmail(false);
    } else {
      alert("Failed to update email: " + JSON.stringify(data));
    }
  };

  // Update password in the backend
  const handlePasswordUpdate = async () => {
    if (newPassword !== confirmPassword) {
      alert("Passwords do not match!");
      return;
    }
    const token = localStorage.getItem("access_token");
    const response = await fetch("http://127.0.0.1:8000/api/profile/password", {
      method: "PUT",
      headers: { 
        "Content-Type": "application/json",
        "Accept": "application/json",
        "Authorization": "Bearer " + token,
      },
      body: JSON.stringify({
        password: newPassword,
        password_confirmation: confirmPassword
      }),
    });
    const data = await response.json();
    if (response.ok) {
      alert("Password updated successfully!");
      setEditPassword(false);
      setNewPassword('');
      setConfirmPassword('');
    } else {
      alert("Failed to update password: " + JSON.stringify(data));
    }
  };

  if (!profile) {
    return <div>Loading profile...</div>;
  }

  return (
    <div className="App">
      <div className="container">
        <h2>User Profile</h2>
        <div>
          <strong>Name:</strong> {profile.name}
        </div>
        <div>
          <strong>Email:</strong> {profile.email}
        </div>
        <div style={{ marginTop: '20px' }}>
          <button class='submitButton' style={{margin: '1rem'}} onClick={() => setEditEmail(true)}>Change Email</button>
          <button class='submitButton' onClick={() => setEditPassword(true)}>Change Password</button>
        </div>

        {editEmail && (
          <div style={{ marginTop: '20px' }}>
            <h3>Change Email</h3>
            <input type="email" placeholder="New email" value={newEmail} onChange={(e) => setNewEmail(e.target.value)}/>
            <button class='submitButton' style={{margin: '1rem'}} onClick={handleEmailUpdate}>Update Email</button>
            <button onClick={() => setEditEmail(false)}>Cancel</button>
          </div>
        )}

        {editPassword && (
          <div style={{ marginTop: '20px' }}>
            <h3>Change Password</h3>
            <input type="password" placeholder="New password" value={newPassword} onChange={(e) => setNewPassword(e.target.value)} />
            <input type="password" placeholder="Confirm new password" value={confirmPassword} onChange={(e) => setConfirmPassword(e.target.value)} />
            <button class='submitButton' style={{margin: '1rem'}}  onClick={handlePasswordUpdate}>Update Password</button>
            <button onClick={() => setEditPassword(false)}>Cancel</button>
          </div>
        )}
      </div>
    </div>
  );
};

export default Profile;