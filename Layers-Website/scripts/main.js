$(document).ready(function() {
    $(window).scroll(function() {
		var scroll = $("#header").offset().top - $(window).scrollTop();

		$("#header").css('backgroundPosition', "50%" + " " + (Math.round(scroll * 0.5) - 100) + "px");
	});

    $(".navbar-button").mouseenter(function() {
        $(this).find(".navbar-button-text-container").finish().animate({
            "width": "70%",
            "margin-left": "15%",
            "margin-right": "15%"
        }, 300);
    });

    $(".navbar-button").mouseleave(function() {
        $(this).find(".navbar-button-text-container").finish().animate({
            "width": "60%",
            "margin-left": "20%",
            "margin-right": "20%"
        }, 300);
    });

    $("#contact-form-submit-button-container").mouseenter(function() {
        $(this).finish().animate({
            "width": "300px"
        }, 300);
    });

    $("#contact-form-submit-button-container").mouseleave(function() {
        $(this).finish().animate({
            "width": "250px"
        }, 300);
    });

    $("#contact-form-submit-button-container").click(function() {
        angular.element("#content-sectiot").scope().submit();
    });
});
