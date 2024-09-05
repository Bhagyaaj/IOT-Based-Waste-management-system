<?php

$con = mysqli_connect('localhost', 'root', '', 'garbagemsdb');
if (!$con) {
  die('Could not connect: ' . mysqli_error($con));
}

$garbagemsdb = $_GET['garbagemsdb'];
$sql = "INSERT into tblbin (id,distance) values (1,'$garbagemsdb')";

// Output received data
echo "Received data: " . print_r($_GET, true);

if (mysqli_query($con, $sql)) {
  echo "Record updated successfully";
} else {
  echo "Error updating record: " . mysqli_error($con);
}

mysqli_close($con);
?>
