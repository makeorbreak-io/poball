var game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update });
var duck;
var cursors;
var platforms;
// var leftWall;
// var rightWall;
// var bottomWall;
// var topWall;


function preload ()
{
    this.load.spritesheet('duck', 'assets/ducks.png',622,901);
}

function create ()
{
    platforms = game.add.group();
    platforms.enableBody =  true;


    game.physics.startSystem(Phaser.Physics.ARCADE);

    duck = game.add.sprite(10,10,'duck');
    duck.height = 70;
    duck.width = 50;
    duck.animations.add('normal', [0, 1], 60, true);
    duck.animations.play('normal',10,true,false );

    game.physics.arcade.enable(duck);

    cursors = game.input.keyboard.createCursorKeys();
    duck.angle = 90;
}

function update ()
{
    processMovement();
}

function processMovement(){
    duck.body.velocity.x = 0;
    duck.body.velocity.y = 0;
    console.log(duck.body.velocity.y);
    if (cursors.left.isDown) {
        if(duck.body.velocity.y > 0)
            duck.angle = -45;
        else if(duck.body.velocity.y < 0)
            duck.angle = -135;
        duck.body.velocity.x = -200;
    }
    else if (cursors.right.isDown) {
        // if(duck.body.rotation >= -90 && duck.body.rotation <= 89.5)
        //     duck.body.angularVelocity = 200;
        // else if(duck.body.rotation <= -90 || duck.body.rotation >= 90.5)
        //     duck.body.angularVelocity = -200;
        duck.body.velocity.x = 200;
    }
    if (cursors.down.isDown) {
        // if(duck.body.rotation >= 0 && duck.body.rotation <= 179.5)
        //     duck.body.angularVelocity = 200;
        // else if(duck.body.rotation <= 0 && duck.body.rotation >= -179.5)
        //     duck.body.angularVelocity = -200;
        duck.body.velocity.y = 200;
    }
    else if (cursors.up.isDown) {
        // if(duck.body.rotation >= 0.5 && duck.body.rotation <= 180)
        //     duck.body.angularVelocity = -200;
        // else if(duck.body.rotation <= -0.5 && duck.body.rotation >= -180)
        //     duck.body.angularVelocity = 200;

        duck.body.velocity.y = -200;
    }
}