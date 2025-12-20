<?php
// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Retrieve form data
    $username = trim($_POST["username"]);
    $email = trim($_POST["email"]);
    $password = $_POST["password"]; // For security, remember to hash passwords before storing in the database

    // Perform validation (You may need more thorough validation)
    if (empty($username) || empty($email) || empty($password)) {
        // If any field is empty, redirect back to signup page with an error message
        header("Location: signup.html?error=emptyfields");
        exit();
    } else {
        // Redirect to the profile page upon successful signup
        header("Location: profile.html");
        exit();
    }
} else {
    // If user tries to access this script without submitting the form, redirect to signup page
    header("Location: signup.html");
    exit();
}
?>
