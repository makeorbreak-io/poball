


class Player extends Phaser.GameObjects.Sprite {

  constructor(scene, x, y, name) {
    super(x,y, name)
    this.scene = scene
    //scene.add.sprite();
    //this.image = image
    this.x = x
    this.y = y
    this.name = name
    this._playerSpeed = 1.5;
    this.setScale(0.5);

  }

  get playerSpeed() {
    return this._playerSpeed;
  }

  set _playerSpeed(value) {
    this._playerSpeed = value;
  }

  addToScene(){
    this.scene.add(this)
  }

  updateSpeed(){
    this.x += this._playerSpeed
  }

}




// create a new scene named "Game"
let gameScene = new Phaser.Scene('Game');

// game parameters
// gameScene.playerSpeed = 1.5;
// gameScene.enemySpeed = 2;
// gameScene.enemyMaxY = 280;
// gameScene.enemyMinY = 80;
// gameScene.isPlayerAlive = true;

// some parameters for our scene
gameScene.init = function() {

  this.gameObjects = [];



  
  this.enemySpeed = 2;
  this.enemyMaxY = 280;
  this.enemyMinY = 80;
}

gameScene.addPlayers = function(){

  this.gameObjects.add(new Player(this, 40, this.sys.game.config.height / 2, 'player'))

}

gameScene.addEnemies = function(){

  var x = 110
  var y =  100

  var stepX = 80
  var stepY = 20

  for (var i = 0; i < 5; i++) {

    x += stepX
    y += stepY

    this.gameObjects.add(new Enemy(x, y, 'dragon'))    
  }
}

// load asset files for our game
gameScene.preload = function() {

  // load images
  this.load_backgrounds();
};

gameScene.getPlayer = function(){
  for (obj in this.gameObjects){
      if(obj instanceof Player){
        return obj
      }
  }
}

gameScene.getEnemies = function(){
  var enemies = []
    for (obj in this.gameObjects){
      if(obj instanceof Enemy){
        enemies.push(Enemy)
      }
  }
  return enemies
}

gameScene.load_backgrounds = function() {
  this.load.image('background', 'assets/background.png');
  this.load.image('player', 'assets/player.png');
  this.load.image('dragon', 'assets/dragon.png');
  this.load.image('treasure', 'assets/treasure.png');
}

// executed once, after assets were loaded
gameScene.create = function() {

  this.addPlayers();
  this.addEnemies();
  //this.addEntities();

  // background
  let bg = this.add.sprite(0, 0, 'background');

  // change origin to the top-left of the sprite
  bg.setOrigin(0, 0);


  // goal
  this.treasure = this.add.sprite(this.sys.game.config.width - 80, this.sys.game.config.height / 2, 'treasure');
  this.treasure.setScale(0.6);


  // scale enemies
  Phaser.Actions.ScaleXY(this.enemies.getChildren(), -0.5, -0.5);

  // set speeds
  Phaser.Actions.Call(this.enemies.getChildren(), function(enemy) {
    enemy.speed = Math.random() * 2 + 1;
  }, this);

  // player is alive
  this.isPlayerAlive = true;
};

// executed on every frame (60 times per second)
gameScene.update = function() {

  // only if the player is alive
  if (!this.isPlayerAlive) {
    return;
  }

  // check for active input
  if (this.input.activePointer.isDown) {

    // player walks
    this.getPlayer().updateSpeed()
  }

  // treasure collision
  if (Phaser.Geom.Intersects.RectangleToRectangle(this.getPlayer().getBounds(), this.treasure().getBounds())) {
    this.gameOver();
  }

  // enemy movement and collision
  let enemies = this.getEnemies();
  let numEnemies = enemies.length;

  for (let i = 0; i < numEnemies; i++) {

    // move enemies
    enemies[i].y += enemies[i].speed;

    // reverse movement if reached the edges
    if (enemies[i].y >= this.enemyMaxY && enemies[i].speed > 0) {
      enemies[i].speed *= -1;
    } else if (enemies[i].y <= this.enemyMinY && enemies[i].speed < 0) {
      enemies[i].speed *= -1;
    }

    // enemy collision
    if (Phaser.Geom.Intersects.RectangleToRectangle(this.getPlayer().getBounds(), enemies[i].getBounds())) {
      this.gameOver();
      break;
    }
  }
};

gameScene.gameOver = function() {

  // flag to set player is dead
  this.isPlayerAlive = false;

  // shake the camera
  this.cameras.main.shake(500);

  // fade camera
  this.time.delayedCall(250, function() {
    this.cameras.main.fade(250);
  }, [], this);

  // restart game
  this.time.delayedCall(500, function() {
    this.scene.manager.bootScene(this);
  }, [], this);

  // reset camera effects
  this.time.delayedCall(600, function() {
    this.cameras.main.resetFX();
  }, [], this);
};



// our game's configuration
let config = {
  type: Phaser.AUTO,
  width: 640,
  height: 360,
  scene: gameScene
};

// create the game, and pass it the configuration
let game = new Phaser.Game(config);
