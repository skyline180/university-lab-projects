document.addEventListener('DOMContentLoaded', function() {
    // Mock user data - in a real application, fetch this from server
    const user = {
        username: "JohnDoe",
        email: "johndoe@example.com"
    };

    // Update the profile page with user data
    document.getElementById('usernameDisplay').textContent = user.username;
    document.getElementById('emailDisplay').textContent = user.email;
});
