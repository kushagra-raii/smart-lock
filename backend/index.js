import express from "express";
import bodyParser from "body-parser";
import cors from "cors"

const app = express();
const port = process.env.PORT || 3000;

app.use(cors());
// Middleware
app.use(bodyParser.json());

// Secret password (should be stored securely in production)
const SECRET_PASSWORD = "1234";

// Global flag
let isPasswordCorrect = false;

// Set flag timeout (ms)
const FLAG_TIMEOUT = 10000; // 10 seconds

// Route to validate password
app.post("/validate-password", (req, res) => {
  const { password } = req.body;

  if (password === SECRET_PASSWORD) {
    isPasswordCorrect = true;

    // Reset the flag after the timeout
    setTimeout(() => {
      isPasswordCorrect = false;
    }, FLAG_TIMEOUT);

    return res.status(200).json({ success: true, message: "Password correct!" });
  }

  return res.status(401).json({ success: false, message: "Incorrect password" });
});

// Route for ESP32 to check the flag
app.get("/check-flag", (req, res) => {
  return res.status(200).json({ flag: isPasswordCorrect });
});

// Start server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

