<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>File Upload</title>
</head>
<body>
    <form action="" method="POST" enctype="multipart/form-data">
        <h4>Upload Your File:</h4>
        <input type="file" name="fileupload">
        <br>
        <input type="submit" name="submit" value="Upload File">
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (isset($_FILES['fileupload']) && $_FILES['fileupload']['error'] == 0) {
            $file_name = $_FILES['fileupload']['name'];
            $file_size = $_FILES['fileupload']['size'];
            $file_tmp = $_FILES['fileupload']['tmp_name'];
            $file_type = $_FILES['fileupload']['type'];
            $temp = explode('.', $file_name);
            $file_ext = strtolower(end($temp));

            $allowed_extensions = array("gif", "pdf", "doc", "docx", "txt", "zip");

            echo "My File Name: " . $file_name . "<br>";
            echo "My File Size: " . $file_size . " bytes<br>";
            echo "My File Type: " . $file_type . "<br>";
            echo "My File Extension: " . $file_ext . "<br>";
            echo "My File Temp Name: " . $file_tmp . "<br>";

            // Check if the extension is allowed
            if (in_array($file_ext, $allowed_extensions)) {
                echo "File is a valid image format.<br>";
            } else {
                echo "Invalid file format. Allowed formats: jpeg, jpg, png<br>";
            }
        } else {
            echo "No file uploaded or an error occurred.";
        }
    }
    ?>
</body>
</html>
