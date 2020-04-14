const functions = require('firebase-functions');
var admin = require('firebase-admin');
admin.initializeApp(functions.config().firebase);

var database = admin.database();
// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//
 exports.helloWorld = functions.https.onRequest((request, response) => {

    let params = request.body.queryResult.parameters;
    console.log(params);
    let ref=database.ref();
    ref.set(params);
    if(params.hasOwnProperty("status")){
      //setTimeout(() => {}, 8000);
      try{
         ref.on("child_added", function(snapshot, prevChildKey) {
            var newKey = snapshot.val();
         if(newKey.ButtonStatus !== null){
            response.send({
               fulfillmentText: "Button status is " + newKey.ButtonStatus
            });
         }
      });
   }
   catch(error){ console.log("error"); }
   }
    else{
       // Attach an asynchronous callback to read the data at our posts reference
       ref.on("value", function(snapshot) {
         console.log(snapshot.val());
         response.send({
            fulfillmentText: snapshot.val().colour+ " light controlled successfully"
       });
       }, function (errorObject) {
         response.send({
            fulfilementText: "The read failed: " + errorObject.code  
         });
      });
    /*response.send({
         fulfillmentText: "light controlled successfully"
    });*/
   }
 });
