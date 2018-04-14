var game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update });
var duck;
var cursors;
var platforms;
var ball;
// var leftWall;
// var rightWall;
// var bottomWall;
// var topWall;


function preload ()
{
    this.load.image('ball', 'assets/ball.png');
    this.load.spritesheet('duck', 'assets/ducks.png',622,901);
}

function create ()
{
    platforms = game.add.group();
    platforms.enableBody =  true;


    game.physics.startSystem(Phaser.Physics.ARCADE);

    ball = game.add.sprite(500,500, 'ball');

    ball.width = 50;
    ball.height = 50;

    duck = game.add.sprite(50,50,'duck');
    duck.animations.add('normal', [0, 1], 10, true);
    duck.height = 70;
    duck.width = 70;
    game.physics.arcade.enable(duck);
    game.physics.arcade.enable(ball);
    duck.animations.play('normal');
    cursors = game.input.keyboard.createCursorKeys();


    ball.body.setCircle(25);
    duck.body.setCircle(35,100,100);
}

function update ()
{
    game.physics.arcade.collide(duck, ball);
    processMovement();
}

function processMovement(){
    duck.body.velocity.x = 0;
    duck.body.velocity.y = 0;
    if (cursors.down.isDown) {
        duck.body.velocity.y = 200;
    }
    else if (cursors.up.isDown) {
        duck.body.velocity.y = -200;
    }
    if (cursors.left.isDown) {
        duck.body.velocity.x = -200;
    }
    else if (cursors.right.isDown) {
        duck.body.velocity.x = 200;
    }


}