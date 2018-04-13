class FieldObject{
    constructor(game, x, y, pathFile, pathFile2, name, width,height){
        let frameData = new FrameData();
        let frames = [0,1];
        let parent = new Sprite(game,x,y);
        let frame1 = new Frame(0,x,y,width,height,pathFile);
        let frame2 = new Frame(1,x,y,width,height,pathFile2);
        frameData.add(frame1);
        frameData.add(frame2);
        this.animation = new  Animation(game, parent, name, frameData, frames, 60, true);
    }
}