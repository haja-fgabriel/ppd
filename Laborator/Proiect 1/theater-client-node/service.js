var XMLHttpRequest = require('xmlhttprequest').XMLHttpRequest;

const buyTickets = async (ticket) => {
    const k = new XMLHttpRequest();
    var success;
    var answer;
    k.onreadystatechange = () => {
        if (k.readyState == 4) {
            answer = k.responseText;
            success = (k.status == 200);
        }
    };
    k.open("POST", 'http://localhost:8080/sale/add', false);
    k.setRequestHeader('Content-Type', 'application/json');
    k.send(JSON.stringify(ticket));
    if (success) {
        return Promise.resolve(answer);
    } else {
        return Promise.reject(answer);
    }
}

const countPlacesForSpectacle = async (place_id) => {
    const k = new XMLHttpRequest();
    var success;
    var answer;
    k.onreadystatechange = () => {
        if (k.readyState == 4) {
            answer = k.responseText;
            success = (k.status == 200);
        }
    };
    k.open("GET", `http://localhost:8080/theater/${place_id}/count-places`, false);
    k.send('');
    if (success) {
        return Promise.resolve(answer);
    } else {
        return Promise.reject(answer);
    }
}

module.exports = { buyTickets, countPlacesForSpectacle };

