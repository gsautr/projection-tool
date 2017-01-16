#include "ofApp.h"

// base 50, length 225, width 150


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    w = 600;
    h = 600;
    
    rotate = 0.0;
    gui = new ofxDatGui();
    boxBase = gui->addTextInput("Box Lower Height");
    boxBase->setText("50");
    boxAngle = gui->addTextInput("Box Angle");
    boxAngle->setText("20");
    boxWidth = gui->addTextInput("Box Width");
    boxWidth->setText("150");
    boxLength = gui->addTextInput("Box Length");
    boxLength->setText("225");
    ceilingHeight = gui->addTextInput("Ceiling");
    ceilingHeight->setText("272");
    lensOffset = gui->addTextInput("Lens distance");
    lensOffset->setText("40");
    
    
    ofSetWindowShape(w, h);
    fbo.allocate(w, h);
    
    font.load("ofxbraitsch/fonts/Verdana.ttf", 18, true, true);
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    
}

void ofApp::annotate(float x1,float  y1,float  x2,float  y2, ofColor color) {
    
    ofStyle style;
    style.lineWidth = 1;
    style.color = color;
    ofSetColor(style.color);
    ofSetStyle(style);\
    ofDrawLine(0, x1, y1, 0, x2, y2);
    
    ofSpherePrimitive sa, sb;
    sa.setPosition(ofVec3f(0, x1, y1));
    sa.setScale(0.1);
    sa.draw();
    sb.setPosition(ofVec3f(0, x2, y2));
    sb.setScale(0.1);
    sb.draw();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    float width = ofToFloat(boxWidth->getText());
    float floor = ofToFloat(boxBase->getText());
    float angle = ofToFloat(boxAngle->getText());
    float length = ofToFloat(boxLength->getText());
    float ceiling = ofToFloat(ceilingHeight->getText());
    float lens = ceiling - ofToFloat(lensOffset->getText());
    
    ofSpherePrimitive sphere;
    ofMaterial boxMaterial;
    
    
    boxMaterial.setDiffuseColor(ofColor(40));
//    boxMaterial.setShininess(0.02);
    
    
    
    ////// CREATE PLINTH
    
    vector<ofVec3f> points;
    float height = (length * tan(ofDegToRad(angle)));
    points.push_back(ofVec3f(width/2, -(length/2), floor));
    points.push_back(ofVec3f(-(width/2), -(length/2), floor));
    points.push_back(ofVec3f(width/2, (length/2), floor+height));
    points.push_back(ofVec3f(-(width/2), (length/2), floor+height));
    
    
    box.clear();
    box.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    int index = 0;
    for (auto &point: points) {
        
        box.addVertex(point);
        box.addColor(ofColor(255));
        box.addIndex(index++);
    }
    
    ///// CREATE LENS
    ofVec2f a(-(length/2), floor);
    ofVec2f b(length/2, floor + height);
    float anglemidpoint = a.angle(b);
    ofVec2f mid = a.getMiddle(b);
    float spin = 90;
    float x = mid.x + -1000 * cos(ofDegToRad(angle - spin));
    float y = mid.y + -1000 * sin(ofDegToRad(angle - spin));
    ofPoint lenspoint, basepoint, hitpoint;
    ofLineSegmentIntersection(ofPoint(-1000, lens), ofPoint(1000, lens), ofPoint(mid.x, mid.y), ofPoint(x,y), lenspoint);
    ofLineSegmentIntersection(ofPoint(-1000, ceiling), ofPoint(1000, ceiling), ofPoint(mid.x, mid.y), ofPoint(x,y), basepoint);
    ofLineSegmentIntersection(a, b, lenspoint, ofPoint(lenspoint.x, 0), hitpoint);
    
    
    
    rotate += 0.2;
    camera.setPosition(0, -400, floor * 4);
    camera.setTarget(ofVec3f(0,0,floor * 2));
    camera.begin();
    ofPushMatrix();
    ofRotateZ(rotate);
    
    
    
    ofStyle style;
    style.color = ofColor(255,255,255,40);
    style.lineWidth = 1;
    ofSetStyle(style);
    
    ofPlanePrimitive plane;
    int size = 400;
    int res = size / 10;
    plane.set(size, size);
    plane.setResolution(res,res);
    plane.drawWireframe();
    
    
    ofPlanePrimitive roof;
    roof.set(size, size);
    roof.setResolution(res,res);
    roof.setPosition(0, 0, ceiling);
    roof.drawWireframe();
    
    
    
    box.draw();
    
    ofSetColor(0);
    
    
    ///// DRAW PROJECTOR
    
    ofSetColor(0);
    style.color = ofColor(0);
    style.lineWidth = 4;
    ofSetStyle(style);
    ofDrawLine(0, lenspoint.x, lenspoint.y, 0, basepoint.x, basepoint.y);
    ofSpherePrimitive lenssphere;
    
    style.color = ofColor(255,255,0);
    style.lineWidth = 4;
    ofSetStyle(style);
    
    lenssphere.setPosition(ofVec3f(0, lenspoint.x, lenspoint.y));
    lenssphere.setScale(0.1);
    lenssphere.draw();
    float sine = (sin(ofGetElapsedTimef()) + 1) * (lenspoint.y / 2);
    
    annotate(-(length/2), sine, lenspoint.x, sine, ofColor(255,0,0));
    
    annotate(-(length/2), floor, hitpoint.x, hitpoint.y, ofColor(0,0,255));
    
    
    ofPopMatrix();
    camera.end();
    
    float edgedistance = lenspoint.x - -(length/2);
    ofDrawBitmapStringHighlight(ofToString(edgedistance), ofGetWidth() * 0.6, ofGetHeight() * 0.8, ofColor(255,0,0));
    
    float hitdistance = hitpoint.distance(ofPoint(-(length/2), floor));
    ofDrawBitmapStringHighlight(ofToString(hitdistance), ofGetWidth() * 0.8, ofGetHeight() * 0.6, ofColor(0,0,255));
    
    
    
    ofDrawBitmapStringHighlight("Lens", ofGetWidth() * 0.8, ofGetHeight() * 0.2, ofColor(255,255,0), ofColor(0));
//    fbo.begin();
//    ofBackground(255);
//    ofTranslate(ofGetWidth() - (plinthBottomLength + 100), ofGetHeight() - plinth.getBoundingBox().height - 10);
//    
//    ofSetColor(220);
//    ofFill();
//    plinth.draw(); // PLINTH
    
//    fbo.end();
//    fbo.draw(0,0, w, h);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
