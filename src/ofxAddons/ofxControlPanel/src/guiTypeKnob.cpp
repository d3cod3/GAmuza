#include "guiTypeKnob.h"

//------------------------------------------------
void guiTypeKnob::setup(string knobName, float defaultVal, float min, float max){
	value.addValue(defaultVal, min, max);
	name = knobName;
}

//-----------------------------------------------
void guiTypeKnob::updateValue(){
	notify();
}

//-----------------------------------------------.
void guiTypeKnob::updateGui(float x, float y, bool firstHit, bool isRelative){
	if( state == SG_STATE_SELECTED){
		if( !isRelative ){
			float pct = ( x - ( hitArea.x ) ) / hitArea.width;
			value.setValueAsPct( pct );
		}else if( !firstHit ){
			float pct = value.getPct();
			pct += (x * 0.02) / hitArea.width;
			value.setValueAsPct( pct );
		}
		notify();
	}
}

//-----------------------------------------------.
void guiTypeKnob::render(){
	ofPushStyle();
		glPushMatrix();
			guiBaseObject::renderText();
	
			float	w	= hitArea.width / 8;
			float	h	= hitArea.width / 8;
			float	x	= hitArea.x + w;
			float	y	= hitArea.y + h;
			
			float	v1	= 130.0f;
			float	v2	= 280.0f;
			
			int		resolution = 22;
			
			float	angle, step, cosine, sine, xpos, ypos;

			//draw the background
			ofFill();
			glColor4fv(bgColor.getColorF());
			ofEllipse(x, y, w, h);

			//draw the foreground
			glColor4fv(fgColor.getColorF());
			step	= (DEG_TO_RAD * value.getPct() * v2) / (resolution - 1);
			angle	= DEG_TO_RAD * v1;
			
			glBegin(GL_TRIANGLE_STRIP);
			for(int i = 0; i < resolution; i++){
				
				cosine	= cos(angle);
				sine	= sin(angle);
				
				xpos	= cosine * w;
				ypos	= sine * h;
				
				glVertex2f(x + xpos, y + ypos);
				
				xpos	= cosine * (w - 10);
				ypos	= sine * (h - 10);
				
				glVertex2f(x + xpos, y + ypos);
				
				angle += step;
			}
			glEnd();
	
			// handle
			ofNoFill();
			
			angle	= DEG_TO_RAD * v1;
			cosine	= cos(angle);
			sine	= sin(angle);
			
			ofLine(x + cosine * w, y + sine * h, x + cosine * (w - 10), y + sine * (h - 10));
			
			angle	= DEG_TO_RAD * (v1 + value.getPct() * v2);
			cosine	= cos(angle);
			sine	= sin(angle);
			
			ofLine(x + cosine * w, y + sine * h, x + cosine * (w - 10), y + sine * (h - 10));
			
			step	= (DEG_TO_RAD * value.getPct() * v2) / (resolution - 1);
			angle	= DEG_TO_RAD * v1;
			
			glPushMatrix();	
			glTranslatef(x, y, 0.0);
			ofBeginShape();
			
			for(int i = 0; i < resolution; i++)
			{
				xpos	= cos(angle) * (w - 10);
				ypos	= sin(angle) * (h - 10);
				
				ofVertex(xpos, ypos);
				angle += step;
			}
			
			ofEndShape(false);
			glPopMatrix();

			//draw the outline
			glColor4fv(outlineColor.getColorF());
			ofEllipse(x, y, w, h);
		glPopMatrix();
	ofPopStyle();
}
