if (!!window.EventSource) {
    var source = new EventSource('/');
    source.onmessage = function(e) {
      var bumper = e.data[1]
      var cliff = e.data[3];
      var drop = e.data[5];


      // finish the code to handle the bumper status
        if (bumper=="0")
          {
            document.getElementById("butbump").value = "OFF";
          }
        if (bumper=="1")
        {
          document.getElementById("butbump").value = "Right";
        }
        if (bumper=="2")
        {
          document.getElementById("butbump").value = "Center";
        }
        if (bumper=="3")
        {
          document.getElementById("butbump").value = "Right + Center";
        }         
        if (bumper=="4")
          {
            document.getElementById("butbump").value = "Left";
          }        
        if (bumper=="5")
          {
            document.getElementById("butbump").value = "Right + Left PROBLEM!";
          }
        if (bumper=="6")
          {
            document.getElementById("butbump").value = "Lefty + Center";
          }
        if (bumper=="7")
          {
            document.getElementById("butbump").value = "All Bumpers";
          }
          // finish the code to handle the wheel drop status 
      switch(drop){
        case"0": document.getElementById(butwheel).value = "OFF"; break;
        case"1": document.getElementById(butwheel).value = "Right"; break;
        case"2": document.getElementById(butwheel).value = "Left"; break;
        case"3": document.getElementById(butwheel).value = "Both"; break;
       }
      // if (drop=="0")
      //   {
      //     document.getElementById("butcliff").value = "OFF";

      //   }
      //   if (drop=="1")
      //   {
      //     document.getElementById("butcliff").value = "ON";
      //   }
      

      // finish the code to handle cliff status 
      switch(cliff){
        case"0": document.getElementById(butcliff).value = "OFF"; break;
        case"1": document.getElementById(butcliff).value = "Right"; break;
        case"2": document.getElementById(butcliff).value = "Center"; break;
        case"3": document.getElementById(butcliff).value = "Right + Center"; break;
        case"4": document.getElementById(butcliff).value = "Left"; break;
        case"5": document.getElementById(butcliff).value = "Right + Left"; break;
        case"6": document.getElementById(butcliff).value = "Left + Center"; break;
        case"0": document.getElementById(butcliff).value = "ALL"; break;

      }
      // if (cliff=="0")
      //   {
      //     document.getElementById("the id of button where you need to display the sensor status").value = "OFF";
      //   }
      


    }
  }