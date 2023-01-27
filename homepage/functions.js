function switchBack(id, text){
    document.getElementById(id).innerHTML = 'text';
}


function copyIt(id){
    var copyText = document.getElementById(id).innerHTML;
    navigator.clipboard.writeText(copyText);
}

