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
}

function update ()
{
    processMovement();
}

function processMovement(){
    duck.body.velocity.x = 0;
    duck.body.velocity.y = 0;

    if (cursors.left.isDown && !duck.body.touching.left)
    {
        //  Move to the left
        duck.body.velocity.x = -150;
    }
    else if (cursors.right.isDown && !duck.body.touching.right)
    {
        //  Move to the right
        duck.body.velocity.x = 150;
    }
    if (cursors.down.isDown && !duck.body.touching.down)
    {
        duck.body.velocity.y = 150;
    }
    else if (cursors.up.isDown && !duck.body.touching.up)
    {
        duck.body.velocity.y = -150;
    }
}