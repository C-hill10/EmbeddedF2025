if (!!window.EventSource) {
    var source = new EventSource('/');
    source.onmessage = function(e) {
      var bumper = e.data[1];
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
            document.getElementById("butbump").value = "Left + Center";
          }
        if (bumper=="7")
          {
            document.getElementById("butbump").value = "All Bumpers";
          }
          //finish the code to handle the wheel drop status 
      // switch(drop){
      //   case"0": document.getElementById("butwheel").value = "OFF"; break;
      //   case"1": document.getElementById("butwheel").value = "Right"; break;
      //   case"2": document.getElementById("butwheel").value = "Left"; break;
      //   case"3": document.getElementById("butwheel").value = "Both"; break;
      //   default: document.getElementById("butwheel").value = "OFF";
      //  }
      if (drop=="0")
        {
          document.getElementById("butwheel").value = "OFF";

        }
        if (drop=="1")
        {
          document.getElementById("butwheel").value = "Right";
        }
        if (drop=="2")
          {
            document.getElementById("butwheel").value = "Left";
  
          }
        if (drop=="3")
        {
          document.getElementById("butwheel").value = "Both";

        }                   
      // finish the code to handle cliff status 
      // switch(cliff){
      //   case"0": document.getElementById("butcliff").value = "OFF"; break;
      //   case"1": document.getElementById("butcliff").value = "Right"; break;
      //   case"2": document.getElementById("butcliff").value = "Center"; break;
      //   case"3": document.getElementById("butcliff").value = "Right + Center"; break;
      //   case"4": document.getElementById("butcliff").value = "Left"; break;
      //   case"5": document.getElementById("butcliff").value = "Right + Left"; break;
      //   case"6": document.getElementById("butcliff").value = "Left + Center"; break;
      //   case"7": document.getElementById("butcliff").value = "ALL"; break;
      //   default: document.getElementById("butcliff").value = "OFF";
      // }
      if (cliff=="0")
        {
          document.getElementById("butcliff").value = "OFF";
        }
      if (cliff=="1")
        {
          document.getElementById("butcliff").value = "Right";
        }
      if (cliff=="2")
        {
          document.getElementById("butcliff").value = "Center";
        }
      if (cliff=="3")
        {
          document.getElementById("butcliff").value = "Right + Center";
        }
      if (cliff=="4")
        {
          document.getElementById("butcliff").value = "Left";
        }
      if (cliff=="5")
        {
          document.getElementById("butcliff").value = "Right + Left";
        }
      if (cliff=="6")
        {
          document.getElementById("butcliff").value = "Left + Center";
        }
      if (cliff=="7")
        {
          document.getElementById("butcliff").value = "All";
        }

    }
  }