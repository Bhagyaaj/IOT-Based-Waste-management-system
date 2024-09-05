<?php
// Execute the Python script in the background
exec('python C:/xampp/htdocs/gms/driver/opti.py > /dev/null 2>&1 &');

// Redirect the user to the new page
header('Location: optimized_path_image.php');
exit;
?>
