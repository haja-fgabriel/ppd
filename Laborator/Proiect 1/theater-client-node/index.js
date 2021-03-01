var service = require('./service');

if (process.argv.length < 3) {
    console.log('Usage: ' + process.argv[1] + ' <timeout_seconds>');
    process.exit(1);
}

const timeout = process.argv[2] * 1000;

setTimeout(() => {
    process.exit(0);
}, timeout);



// countPlacesForSpectacle(2)
// .then((count)=>{
    // var numberPlaces = Math.floor(Math.random() * count);
    // var placeSales = [];
    // for (; numberPlaces; numberPlaces--) {
    //     placeSales.push();
    // }
    

    setInterval(() => {
        ticket = {
            "spectacleId" : 1,
            "sellingDate" : "2018-10-01",
            "placeSales"  : [1, 2, 3]
        }
        
        service.buyTickets(ticket)
        .then((ans) => console.log(`ticket sale ok, id: ${ans}`))
        .catch((reason) => console.log(`ticket sale failed, reason: ${reason}`));
        
        console.log('it really is an asynchronous function');

        ticket = {
            "spectacleId" : 2,
            "sellingDate" : "2018-10-01",
            "placeSales"  : [1, 2, 3]
        }
        
        service.buyTickets(ticket)
        .then((ans) => console.log(`ticket sale ok, id: ${ans}`))
        .catch((reason) => console.log(`ticket sale failed, reason: ${reason}`));
        
        console.log('it really is an asynchronous function');

        ticket = {
            "spectacleId" : 3,
            "sellingDate" : "2018-10-01",
            "placeSales"  : [1, 2, 3]
        }
        
        service.buyTickets(ticket)
        .then((ans) => console.log(`ticket sale ok, id: ${ans}`))
        .catch((reason) => console.log(`ticket sale failed, reason: ${reason}`));
        
        console.log('it really is an asynchronous function');
        
    }, 2000);
// })
// .catch((_error)=>{});


