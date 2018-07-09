#include "views.h"

Views* Views::instance = 0;

Views* Views::getInstance()
{
  if (instance == 0)
  {
    instance = new Views();  
  }
  return instance;
}

Views::Views() {}

std::string Views::configPage(std::string deviceName, std::vector <std::string> availableNetworks, std::string wifiName, std::string wifiPass)
{
  std::string content;
  content = "<!DOCTYPE html>";
  content += "<html>";
  content += "<head>";
  content += "<meta charset=\"utf-8\" />";
  content += "<title>HomeGrid device configuration page</title>";

  content += style();

  content += "</head>";

  content += "<body>";

  content += "<div id=\"contact\">";
  content += "  <h1>HomeGrid</h1>";
  content += "<form action=\"set\" method=\"post\">";
  content += "    <fieldset>";
  
  content += "  <h2>Device settings</h2>";
  content += "      <label for=\"name\">Name:</label>";
  content += "      <input type=\"text\" name=\"name\" id=\"name\" placeholder=\"Unique name for this device\" value=\"" + deviceName + "\"/>";

  content += "  <h2>WiFi settings</h2>";
  content += "      <label for=\"network\">Network:</label>";
  content += "      <select name=\"network\" id=\"network\"/>";

  for (std::string network : availableNetworks) {
    if (network == wifiName) {
      content += "        <option value=\"" + network + "\" selected>" + network + "</option>";
    } else {
      content += "        <option value=\"" + network + "\">" + network + "</option>"; 
    }
  }
  
  content += "      </select>";

  content += "      <label for=\"password\">Password:</label>";
  content += "      <input type=\"password\" name=\"pass\" id=\"password\" placeholder=\"WiFi password\" value = \"" + wifiPass + "\"/>";

  content += "  <h2>MQTT settings</h2>";
      
  content += "      <label for=\"mqtt_server\">Server:</label>";
  content += "      <input type=\"text\" id=\"mqtt_server\" placeholder=\"Server name (FQDN)\" />";

  content += "      <label for=\"mqtt_fingerprint\">Certificate:</label>";
  content += "      <input type=\"text\" id=\"mqtt_fingerprint\" placeholder=\"Server certificate fingerprint\" />";
  
  content += "      <label for=\"mqtt_user\">Username:</label>";
  content += "      <input type=\"text\" id=\"mqtt_server\" placeholder=\"Enter the username\" />";
  
  content += "      <label for=\"mqtt_password\">Password:</label>";
  content += "      <input type=\"password\" id=\"mqtt_server\" placeholder=\"Enter the password\" />";
      
  content += "      <input type=\"submit\" value=\"Save\" />";
      
  content += "    </fieldset>";
  content += "  </form>";
  content += "</div>";

  content += "</body>";
  content += "</html>";

  return content;
}

std::string Views::rebootPage()
{
  std::string content;
  content = "<!DOCTYPE html>";
  content += "<html>";
  content += "<head>";
  content += "<meta charset=\"utf-8\" />";
  content += "<title>HomeGrid device configuration page</title>";

  content += style();
  
  content += "</head>";

  content += "<body>";

  content += "<div id=\"contact\">";
  content += "  <h1>Rebooting...</h1>";
  content += "</div>";

  content += "</body>";
  content += "</html>";

  return content;
}

std::string Views::style()
{
  std::string content;
  content += "<style>";
  content += "body, div, h1, form, fieldset, input, textarea {";
  content += "  margin: 0; padding: 0; border: 0; outline: none;";
  content += "}";

  content += "html {";
  content += "  height: 100%;";
  content += "}";

  content += "body {";
  content += "  background: #728eaa;";
  content += "  background: -moz-linear-gradient(top, #25303C 0%, #728EAA 100%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#25303C), color-stop(100%,#728EAA)); /* webkit */";
  content += "  font-family: sans-serif;"; 
  content += "}";

  content += "#contact {";
  content += "  width: 430px; margin: 10px auto; padding: 60px 30px;";
  content += "  background: #c9d0de; border: 1px solid #e1e1e1;";
  content += "  -moz-box-shadow: 0px 0px 8px #444;";
  content += "  -webkit-box-shadow: 0px 0px 8px #444;";
  content += "}";

  content += "h1 {";
  content += "  font-size: 35px; color: #445668;";
  content += "  text-align: center; margin: 0 0 35px 0; text-shadow: 0px 1px 0px #f2f2f2;";
  content += "}";

  content += "h2 {";
  content += "  font-size: 20px; color: #445668;";
  content += "  text-align: left; margin: 20px 0 10px 120px; text-shadow: 0px 1px 0px #f2f2f2;";
  content += "}";

  content += "label {";
  content += "  float: left; clear: left; margin: 11px 20px 0 0; width: 95px;";
  content += "  text-align: right; font-size: 16px; color: #445668;";
  content += "        text-shadow: 0px 1px 0px #f2f2f2;";
  content += "}";

  content += "select {";
  content += "  width: 300px; height: 40px; padding: 5px 20px 0px 20px; margin: 0 0 20px 0;";
  content += "  background: #5E768D;";
  content += "  background: -moz-linear-gradient(top, #546A7F 0%, #5E768D 20%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#546A7F), color-stop(20%,#5E768D)); /* webkit */";
  content += "  border-radius: 5px; -moz-border-radius: 5px; -webkit-border-radius: 5px;";
  content += "  -moz-box-shadow: 0px 1px 0px #f2f2f2;-webkit-box-shadow: 0px 1px 0px #f2f2f2;";
  content += "  font-family: sans-serif; font-size: 16px; color: #f2f2f2; text-shadow: 0px -1px 0px #334f71; ";
  content += "}";

  content += "input {";
  content += "  width: 260px; height: 35px; padding: 5px 20px 0px 20px; margin: 0 0 20px 0;";
  content += "  background: #5E768D;";
  content += "  background: -moz-linear-gradient(top, #546A7F 0%, #5E768D 20%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#546A7F), color-stop(20%,#5E768D)); /* webkit */";
  content += "  border-radius: 5px; -moz-border-radius: 5px; -webkit-border-radius: 5px;";
  content += "  -moz-box-shadow: 0px 1px 0px #f2f2f2;-webkit-box-shadow: 0px 1px 0px #f2f2f2;";
  content += "  font-family: sans-serif; font-size: 16px; color: #f2f2f2; text-shadow: 0px -1px 0px #334f71; ";
  content += "}";
  content += "  input::-webkit-input-placeholder  {";
  content += "      color: #a1b2c3; text-shadow: 0px -1px 0px #38506b;";
  content += "  }";
  content += "  input:-moz-placeholder {";
  content += "      color: #a1b2c3; text-shadow: 0px -1px 0px #38506b;";
  content += "  }";

  content += "textarea {";
  content += "  width: 260px; height: 170px; padding: 12px 20px 0px 20px; margin: 0 0 20px 0;";
  content += "  background: #5E768D;";
  content += "  background: -moz-linear-gradient(top, #546A7F 0%, #5E768D 20%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#546A7F), color-stop(20%,#5E768D)); /* webkit */";
  content += "  border-radius: 5px; -moz-border-radius: 5px; -webkit-border-radius: 5px;";
  content += "  -moz-box-shadow: 0px 1px 0px #f2f2f2;-webkit-box-shadow: 0px 1px 0px #f2f2f2;";
  content += "  font-family: sans-serif; font-size: 16px; color: #f2f2f2; text-shadow: 0px -1px 0px #334f71;";
  content += "}";
  content += "  textarea::-webkit-input-placeholder  {";
  content += "      color: #a1b2c3; text-shadow: 0px -1px 0px #38506b;";
  content += "  }";
  content += "  textarea:-moz-placeholder {";
  content += "      color: #a1b2c3; text-shadow: 0px -1px 0px #38506b;";
  content += "  }";
  
  content += "input:focus, textarea:focus {";
  content += "  background: #728eaa;";
  content += "  background: -moz-linear-gradient(top, #668099 0%, #728eaa 20%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#668099), color-stop(20%,#728eaa)); /* webkit */";
  content += "}";

  content += "input[type=submit] {";
  content += "  width: 150px; height: 40px; float: right; padding: 10px 15px; margin: 35px 5px 0 0;";
  content += "  -moz-box-shadow: 0px 0px 5px #999;-webkit-box-shadow: 0px 0px 5px #999;";
  content += "  border: 1px solid #556f8c;";
  content += "  background: -moz-linear-gradient(top, #718DA9 0%, #415D79 100%); /* firefox */";
  content += "  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,#718DA9), color-stop(100%,#415D79)); /* webkit */";
  content += "  cursor: pointer;";
  content += "}";

  content += "</style>";
  return content;
}

