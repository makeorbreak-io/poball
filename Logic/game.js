var game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update });
var cursors;
var platforms;
WEB_SOCKET_SWF_LOCATION = "net/web_socket/WebSocketMain.swf";
var ws;
var players = {};
players[0] = [];
players[1] = [];
var my_id = 0;
var my_team = 0;

function preload () {
    this.load.spritesheet('duck', 'assets/ducks.png',622,901);
}

function create () {
  ws = new WebSocket("ws://172.29.4.45:8080/");
  ws.onmessage = function(msg) {
    console.log("GOT ' " + msg.data + "'");
    response = JSON.parse(msg.data);

    if (response["register"] !== undefined) {
      let reg = response["register"],
          x = reg["X"], y = reg["Y"];
      registerDuck(x, y, reg["team"], reg["player_id"]);
    }
    else if (response["id"] !== undefined) {
      my_id = response["id"];
      my_team = response["team"];
    }
    else if (response["movement"] !== undefined) {
      let reg = response["movement"],
        x = reg["x_diff"], y = reg["y_diff"];

      processRemoteMovement(reg["team"], reg["player_id"], x, y);
    }
  }
    platforms = game.add.group();
    platforms.enableBody =  true;
    game.physics.startSystem(Phaser.Physics.ARCADE);


    cursors = game.input.keyboard.createCursorKeys();
    // console.log(duck.body.rotation);
}

function update () {
    processLocalMovement();
}

function processRemoteMovement(team, player_id, x_diff, y_diff) {
  let duck = players[team][player_id];
  if (duck === undefined || duck === null || (team == my_team && player_id == my_id) ) {
    return;
  }

  if (x_diff < 0 && !duck.body.touching.left) {
      duck.body.velocity.x = -150;
  }
  else if (x_diff > 0 && !duck.body.touching.right) {
      duck.body.velocity.x = 150;
  }
  if (y_diff > 0 && !duck.body.touching.down) {
      duck.body.velocity.y = 150;
  }
  else if (y_diff < 0 && !duck.body.touching.up) {
      duck.body.velocity.y = -150;
  }

}

function processLocalMovement() {
  let duck = players[my_team][my_id];
  if (duck === undefined || duck === null) {
    return;
  }
  duck.body.velocity.x = 0;
  duck.body.velocity.y = 0;
  let x = duck.position.x,
      y = duck.position.y,
      x_diff, y_diff;


  if (cursors.left.isDown && !duck.body.touching.left) {
      duck.body.velocity.x = -150;
      x_diff = -1;
  }
  else if (cursors.right.isDown && !duck.body.touching.right) {
      duck.body.velocity.x = 150;
      x_diff = 1;
  }
  if (cursors.down.isDown && !duck.body.touching.down) {
      duck.body.velocity.y = 150;
      y_diff = 1;
  }
  else if (cursors.up.isDown && !duck.body.touching.up) {
      duck.body.velocity.y = -150;
      y_diff = -1;
  }
  if (x_diff !== undefined && y_diff !== undefined) {
    ws.send('{"movement":{"team":' + my_team + ', "player_id":' + my_id + ', "x_diff":' + x_diff + ', "y_diff": ' + y_diff + '}}');
  }
}


function newDuck(x, y) {
  ret = game.add.sprite(x, y, 'duck');
  ret.height = 70;
  ret.width = 50;
  ret.animations.add('normal', [0, 1], 60, true);
  ret.animations.play('normal', 4, true, false);
  return ret;
}

function registerDuck(x, y, team, player_id) {
  let duck = newDuck(x, y);
  game.physics.arcade.enable(duck);
  players[team][player_id] = duck;
}
