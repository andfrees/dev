<?php

if($_GET["name"] == 'hao'){

$file = fopen("data.txt", "r") or exit("Unable to open file!");
//Output a line of the file until the end is reached
while(!feof($file))
{
  $text = fgets($file);
  echo $text;
  if(strpos($text, "Copyright")) break;
}
fclose($file);

}

?>
