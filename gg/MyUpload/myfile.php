<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form action="#" method="POST" enctype="multipart/form-data">
        <label for="f">Upload your file</label> <br>
        <input type="file" name="fileupload"> <br>
        <input type="submit" name="submit" value="upload">
    </form>

    <?php

    if($_SERVER['REQUEST_METHOD'] == "POST")
    {
        if(isset($_POST['submit']))
        {
            $filename = $_FILES['fileupload']['name'];
            $filetype = $_FILES['fileupload']['type'];
            $filesize = $_FILES['fileupload']['size'];
            $fileerror = $_FILES['fileupload']['error'];
            $filetmpname = $_FILES['fileupload']['tmp_name'];
            
            // echo "My file name is " . $filename . "<br>";
            // echo "My file type is " . $filetype . "<br>";
            // echo "My file size is " . $filesize . "<br>";
            // echo "My file error is " . $fileerror . "<br>";
            // echo "My file temo name is " . $filetmpname . "<br>";
            // $extension = explode('.', $filename);
            // echo "My file extension is " . $extension[1] . "<br>";
            $fileext = pathinfo($filename, PATHINFO_EXTENSION);
            // echo "My file extension is " . $fileext . "<br>";

            // if(!is_dir("myuploads"))
            // {
            //     if(mkdir("myuploads", 0755, true))
            //     {
            //         echo "directory created successfully<br>";
            //     }
            //     else
            //     {
            //         echo "directory is not created<br>";
            //     }

            //     if(move_uploaded_file($filetmpname, "myuploads/" . basename($filename)))
            //     {
            //         echo "file uploaded successfully<br>";
            //     }
            //     else
            //     {
            //         echo "file is not uploaded<br>";
            //     }
            // }

            if($filesize > 10)
            {
                echo "The file size is " . $filesize . "<br>";
                echo "File size is exceeding the limit. <br>";
            }
            $allowedfiletype = ["pdf"];
            if(!in_array($fileext, $allowedfiletype))
            {
                echo "File type is not allowed";
            }
        }
    }

    ?>


</body>
</html>