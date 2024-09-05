<?php

$con = mysqli_connect('localhost','root','','cm');
if (!$con) {
  die('Could not connect: ' . mysqli_error($con));
}
$cm =$_GET['cm'];

$sql = "UPDATE lenth SET cm='$cm' WHERE id=1";

if (mysqli_query($con, $sql)) {
  echo "Record updated successfully";
} else {
  echo "Error updating record: " . mysqli_error($conn);
}


mysqli_close($con);
?>