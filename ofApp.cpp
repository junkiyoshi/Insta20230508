#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");
	
	ofBackground(239);
	ofSetColor(0, 0, 255);
	ofNoFill();
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(139);

	noise_param += 0.013;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5 + glm::vec2(0, -50));

	vector<ofColor> color_list;
	for (int value = 192; value >= 0; value -= 16) {

		color_list.push_back(ofColor(0, 0, value));
	}

	float scale_span = 5;
	float deg_span = 5;

	for (int i = 0; i < color_list.size(); i++) {
	
		ofMesh mesh;
		float noise_seed = ofRandom(1000);
		for (float scale = 5; scale < 20; scale += scale_span) {

			for (float deg = 0; deg < 360; deg += deg_span) {

				auto noise_location = this->make_point((deg + deg_span * 0.5) * DEG_TO_RAD) * (scale + scale_span * 0.5);
				auto noise_value = ofNoise(noise_seed, noise_location.x * 0.005, noise_location.y * 0.005, noise_param);

				if (noise_value > 0.485 && noise_value < 0.515) {

					mesh.addVertex(this->make_point(deg * DEG_TO_RAD) * scale);
					mesh.addVertex(this->make_point((deg + deg_span) * DEG_TO_RAD) * scale);
					mesh.addVertex(this->make_point((deg + deg_span) * DEG_TO_RAD) * (scale + scale_span));
					mesh.addVertex(this->make_point(deg * DEG_TO_RAD) * (scale + scale_span));

					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);
					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);

					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
				}
			}
		}
		mesh.draw();
	}

	ofBeginShape();
	for (float deg = 0; deg < 360; deg += 1) {

		ofVertex(this->make_point(deg * DEG_TO_RAD) * 20);
	}
	ofEndShape(true);

}

//--------------------------------------------------------------
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec3 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec3(x, -y, 0);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}