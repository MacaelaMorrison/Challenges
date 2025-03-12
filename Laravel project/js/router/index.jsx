import React from 'react';
import {Routes, Route} from 'react-router-dom';

import HomePage from '../components/HomePage';
import RegisterPage from '../components/RegisterPage';
import ProfilePage from '../components/UserProfile';

const Index = () => {
    return (
        <div>
            <Routes>
                <Route path="/" element={<HomePage />}/>
                <Route path="/register" element={<RegisterPage />}/>
                <Route path="/profile" element={<ProfilePage />}/>
            </Routes>
        </div>
    )
}

export default Index