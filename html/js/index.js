(function() {
  // PHPのURL
  var PHP_URL = "ledSet.php";
  // ボタン
  var btn;

  $(function() {
    btn = $("#btn");
    btn.on("click", clickHandler);

    // LEDをOFFにする
    ledSet("OFF");
  });

  /**
   * Click Handler
   */
  function clickHandler() {
    // ON -> OFF
    if(btn.attr("class") == "on") {
      btn.attr("class", "off");
      ledSet("OFF");
    }
    // OFF -> ON
    else {
      btn.attr("class", "on");
      ledSet("ON");
    }
  }

  /**
   * PHPにLEDの状態を送信します
   * @param	state	0:OFF, 1:ON
   */
  function ledSet(state) {
    $.ajax({
      url: PHP_URL,
      type: "post",
      dataType: "json",
      data: {
        state: state
      }
    })
  }
})();