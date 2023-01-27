
$(document).ready(function(){
    $(".email").click(function(){
        $("#copied").fadeIn("slow");
        $("#copied").delay(2000).fadeOut(3000);
    });
});

$(document).ready(function(){
    $(".phone").click(function(){
        $("#copied").fadeIn("slow");
        $("#copied").delay(2000).fadeOut(3000);

    });
});

$(document).ready(function(){
    $("#pc, #qhst, #alc, #bshs").hover(function(){
      $(this).css("border-style", "solid");
      }, function(){
      $(this).css("border-style", "hidden");
    });
  });
