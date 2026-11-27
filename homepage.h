// PART 1: Stops right inside the empty value cell
String homePagePart1 = F(R"=====( 
<!DOCTYPE html> 
<html lang="en" > <!-- Needed for Screenreaders !--> 
<head> 
<!-- UTF-8 character set covers most characters in the world --> 
  <meta charset="utf-8"> 
  <!-- Make page respond to screen size !--> 
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover"> 
  
<!-- Title favicon etc --> 
<title> Smart Humidifier - ESP32 </title> 
<style> 
   body {        
     background-color: DodgerBlue; 
   } 
   .flex-Container{ 
     display: flex; 
     flex-direction: column; 
     background-color: DodgerBlue; 
     align-items: center; 
   } 
   h1{ 
     font: bold; 
     font-size: 40px; 
     font-family: Arial; 
     color: navy; 
     text-align: center; 
   } 
   p{ 
     font-size: 25px; 
     font-family: Arial; 
     color: navy; 
     text-align: center; 
   }   
   th, td { 
     font-size: 25px; 
     padding: 8px; 
     text-align: left; 
     border-bottom: 1px solid #ddd; 
   } 
</style> 
</head> 
 <body> 
  <div class="flex-Container"> 
  <h1> Smart Humidifier Data Display </h1> 
       
  <p>this Webpage displays the various types of data collected by the sensors on the esp32 chip.</p>
  <p>Values are updated automatically every 3 seconds.</p> 
     
  <table> 
        <tr> 
          <th>Sensor</th> 
          <th>Value</th> 
          <th>Unit</th> 
        </tr> 
        <tr> 
          <td> GDHT11 -Temperature</td> 
          <td id="tempValue">
)====="); 

// PART 2: Starts by closing the value cell and adding the unit cell
String homePagePart2 = F(R"=====(</td> 
          <td>Degree Cel</td> 
        </tr>
        <tr>
          <td> GDHT11 - Humidity</td>
          <td> ghhes </td>
          <td>Percentage</td>
        </tr>
        <tr>
          <td> GWLS - Water Level</td>
          <td> ghhses </td>
          <td>Centimeter</td>
        </tr>  
      </table> 
     </div> 

<p>G00475000@atu.ie -  2026 </p> 
  <script>
    setInterval(function() {
      fetch('/temp')
        .then(response => response.text())
        .then(data => {
          document.getElementById('tempValue').innerText = data;
        });
    }, 3000);
  </script>
 </body> 
</html> 
)=====");
