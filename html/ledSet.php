<?php
header("Content-type: text/plain; charset=UTF-8");
if (isset($_POST['state']))
{
  $state = $_POST['state'];
  // ledLog.txtにデータを保存
  $fp = fopen("ledLog.txt", "w");
  fwrite($fp, $state);
  fclose($fp);
}
?>