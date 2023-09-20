#include "ofApp.h"
#include <glm/gtx/matrix_decompose.hpp>


//--------------------------------------------------------------
void ofApp::setup() {
	gui_.setup();

	cam_.disableMouseInput();
	cam_.setPosition({ 0,0,100 });
	cam_.lookAt({ 0,0,0 });

	op_ = ImGuizmo::TRANSLATE;
	mode_ = ImGuizmo::LOCAL;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::drawDebug() {
	string s = "";
	s += "\n";
	s += "KEYS: \ne | r | t\n";
	s += "BACKSPACE: Reset\n";
	s += "\n";
	switch (op_)
	{
	case ImGuizmo::TRANSLATE:
		s += "TRANSLATE";
		break;
	case ImGuizmo::ROTATE:
		s += "ROTATE";
		break;
	case ImGuizmo::SCALE:
		s += "SCALE";
		break;
	}
	s += "\n\n";
	s += "Transformation:\n" + ofToString(node_.getGlobalTransformMatrix()) + "\n";
	s += "Scale:\n" + ofToString(node_.getGlobalScale()) + "\n";
	s += "Rotation:\n" + ofToString(node_.getGlobalOrientation()) + "\n";
	s += "\n";
	if (mode_ == ImGuizmo::LOCAL) s += "LOCAL\n";
	else if (mode_ == ImGuizmo::WORLD) s += "WORLD\n";
	ofDrawBitmapStringHighlight(s, 10, 20);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawDebug();

	//--

	// Using helpers
#if 1
	cam_.begin();
	{
		// Applies the node's transformation matrix
		ImGuizmo::beginGuizmoTransform(&node_);
		{
			ofPushStyle();
			ofNoFill();
			ofDrawBox(25);
			//node_.draw();
			ofPopStyle();
		}
		ImGuizmo::endGuizmoTransform();
	}
	cam_.end();

	ImGuizmo::drawImGuizmo(&gui_, &cam_, &node_, op_, mode_);

	//--

#else
	cam_.begin();
	{
		// Applies the node's transformation matrix
		ofPushMatrix();
		node_.transformGL();  
		{
			ofPushStyle();
			ofNoFill();
			ofDrawBox(25);
			//node_.draw();
			ofPopStyle();
		}
		ofPopMatrix();
	}
	cam_.end();
	
	//--

	gui_.begin();
	{
		ImGuizmo::BeginFrame();
		auto mat = node_.getLocalTransformMatrix();
		if (ImGuizmo::Manipulate(cam_, mat, op_, mode_)) {
			glm::mat4 transformation;
			glm::vec3 scale;
			glm::quat rotation;
			glm::vec3 translation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(mat, scale, rotation, translation, skew, perspective);
			node_.setPosition(translation);
			node_.setScale(scale);
			node_.setOrientation(rotation);
		}
	}
	gui_.end();
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case 'w': op_ = ImGuizmo::TRANSLATE; break;
	case 'e': op_ = ImGuizmo::SCALE; break;
	case 'r': op_ = ImGuizmo::ROTATE; break;

	case ' ': mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL; break;

	case OF_KEY_BACKSPACE: {//reset ofNode
		node_.setPosition(glm::vec3{ 0,0,0 });
		node_.setScale(glm::vec3{ 1,1,1 });
		node_.setOrientation(glm::quat{ 0,0,0,0 });
	}break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
