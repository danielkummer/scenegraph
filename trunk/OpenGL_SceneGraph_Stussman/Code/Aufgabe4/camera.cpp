void camera() {
	static bool initCamera = true;
	static GLfloat cam_matrix[16]; 

	if (initCamera){									// Only on the fist loop
		glPushMatrix();
		glLoadIdentity();								// load identity matrix ...
		glTranslated(0.0, 0.0, -10.0);					// Move camera back a bit
		glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);	// ... and write it in the camera matrix
		glPopMatrix();
		initCamera = false;
	}

	glPushMatrix();
	glLoadMatrixf(cam_matrix);							//load camera matrix

    if (keyFlag.pageUp)   glTranslated(0.0, 0.0,  0.3);  //translate in z direction
    if (keyFlag.pageDown) glTranslated(0.0, 0.0, -0.3);  //translate in z direction

    if (keyFlag.left)  glRotated( 1.5, 0.0, 1.0, 0.0);	//rotate around y-axis
    if (keyFlag.right) glRotated(-1.5, 0.0, 1.0, 0.0);	//rotate around y-axis

    if (keyFlag.up)   glRotatef( 1.5, 1.0, 0.0, 0.0);	//rotate around x-axis
    if (keyFlag.down) glRotatef(-1.5, 1.0, 0.0, 0.0);	//rotate around x-axis

    glGetFloatv(GL_MODELVIEW_MATRIX, cam_matrix);		//write back to camera matrix

    glPopMatrix();

    //set the view
    gluLookAt(cam_matrix[12], cam_matrix[13], cam_matrix[14],   // Position
              cam_matrix[12]+cam_matrix[8],						// View
              cam_matrix[13]+cam_matrix[9],
              cam_matrix[14]+cam_matrix[10],
              cam_matrix[4], cam_matrix[5], cam_matrix[6]);		// UpVector
}