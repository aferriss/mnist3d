#include "ofApp.h"

const int nump = 2500;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBuffer bufferX = ofBufferFromFile("mnistX.txt");
    ofBuffer bufferY = ofBufferFromFile("mnistY.txt");
    ofBuffer bufferZ = ofBufferFromFile("mnistZ.txt");
    
    if(bufferX.size()){
        for(ofBuffer::Line it = bufferX.getLines().begin(), end = bufferX.getLines().end(); it != end; it++){
            float line = ofToFloat(*it);
            if(line != 0){
                xpos.push_back(line);
            }
        }
    }
    
    if(bufferY.size()){
        for(ofBuffer::Line it = bufferY.getLines().begin(), end = bufferY.getLines().end(); it != end; it++){
            float line = ofToFloat(*it);
            if(line != 0){
                ypos.push_back(line);
            }
        }
    }
    
    if(bufferZ.size()){
        for(ofBuffer::Line it = bufferZ.getLines().begin(), end = bufferZ.getLines().end(); it != end; it++){
            float line = ofToFloat(*it);
            if(line != 0){
                zpos.push_back(line);
            }
        }
    }
    
    ofDisableArbTex();
    tex.load("img0.jpg");
    
    glPointSize(20);
    
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for(int i = 0; i<nump; i++){
        ofVec3f p = ofVec3f(xpos[i], ypos[i], zpos[i])*100;
        ofMesh pMesh;
        pMesh.clear();
        pMesh.setMode(OF_PRIMITIVE_POINTS);
        particles.push_back(pMesh);
        particles[i].addVertex(p);
        
        ofImage im;
        im.load("numbers/img"+ ofToString(i) +".jpg");
        im.resize(32, 32);
        numberImages.push_back( im );
    }
    
    recorder.setVideoCodec("mpeg4");
    recorder.setVideoBitrate("50000k");
    save = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(save){
        ofImage savepix;
        savepix.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        recorder.addFrame(savepix.getPixels());
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
        cam.begin();
    
            for(int i = 0; i<nump; i++){
                numberImages[i].getTexture().bind();
                    ofPushMatrix();
                        ofRotate(ofGetFrameNum()*0.08, 0, 1, 0);
                        particles[i].drawFaces();
                    ofPopMatrix();
                numberImages[i].getTexture().unbind();
            }
    
        cam.end();
    ofDisablePointSprites();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        recorder.setup("mnist3d_"+ofGetTimestampString()+".mp4", ofGetWidth(), ofGetHeight(), 30);
        recorder.start();
        save = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------

void ofApp::exit(){
    recorder.close();
}