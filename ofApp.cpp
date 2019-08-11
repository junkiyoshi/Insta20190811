#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<char> charactors = {
		'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R',
		'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '!' };

	for (int char_index = 0; char_index < charactors.size(); char_index++) {

		ofPoint location = ofPoint(char_index % 6 * this->font_size * 1.2 + this->font_size * 0.7, char_index / 6 * this->font_size * 1.4 + this->font_size * 0.7);
		ofPushMatrix();
		ofTranslate(location);

		auto path = font.getCharacterAsPoints(charactors[char_index], true, false);
		auto outline = path.getOutline();

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(100);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto point = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(string{ charactors[char_index] }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ charactors[char_index] }) * 0.5, 0);
				int len = glm::length(point);
				auto noise_value = ofNoise(location.x, location.y, len * 0.005, ofGetFrameNum() * 0.008);

				if (noise_value <= 0.35) {

					auto rotation_z = glm::rotate(glm::mat4(), ofMap(noise_value, 0.0, 0.35, -PI, 0), glm::vec3(0, 0, 1));
					point = glm::vec4(point, 0) * rotation_z;
					ofVertex(glm::vec3(point));
				}
				else if (noise_value >= 0.65) {

					auto rotation_z = glm::rotate(glm::mat4(), ofMap(noise_value, 0.65, 1.0, 0, PI), glm::vec3(0, 0, 1));
					point = glm::vec4(point, 0) * rotation_z;
					ofVertex(glm::vec3(point));
				}
				else {

					ofVertex(glm::vec3(point));
				}
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}