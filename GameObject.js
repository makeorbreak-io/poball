
class GameObject {
  contructor(physics, graphics, logic) {
    this.physics = physics;
    this.graphs = graphics;
    this.logic = logic;
  }

  gameLoop() {

    while (true) {
      this.physics.check(this.logic.get());

      this.graphs.draw();
    }
  }
}
