<!DOCTYPE html>
<html>
   <script type="text/javascript" src="js/jquery.min.js"></script>
    <script type="text/javascript" src="js/jquery-3.1.1.min.js"></script>
    <script type="text/javascript" src="js/jquery-3.6.0.min.js"></script>
	
<head>
<script>
         $(document).ready(function(){
             setInterval(() => {
                $.ajax({
                    url: 'get.php',
                    type: 'post',
                    success: function(response){
                       
                  $(".handle").css({"width" : response});
                      
                    }
                });
             }, 1000);
         });
     </script>
	<style>
	.bar {
  -webkit-transition: width 0.5s ease !important;
     -moz-transition: width 0.5s ease !important;
       -o-transition: width 0.5s ease !important;
          transition: width 0.5s ease !important;
}
		p {
			font-size: 20px;
		}
	
		.container {
			background-color: rgb(192, 192, 192);
			width: 98%;
				border-radius: 15px;
				position: absolute;
				top:36%;
		}
	
		.skill {
			background-color: rgb(116, 194, 92);
			color: white;
			padding: 1%;
			text-align: right;
			font-size: 20px;
				
		}
	
		.html {
			width: 80%;
		}
	
		.php {
			width: 60%;
		}
	</style>
</head>

<body>
	<center><h1>Nodemcu CM Level Ultra Sonic</h1></center>
	
	<div class="container">
		<div id="Mname"  class="skill handle bar">CM</div>
	</div>
<img src="ruler_PNG82.png" style="position: absolute;  top: 0%;" alt="Nature" class="responsive" width="98%" height="400">
	

</body>
</html>
