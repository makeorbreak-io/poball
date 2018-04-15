class Player extends Phaser.GameObjects.Sprite {

  constructor(scene, x, y, name) {
    
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