#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Game config */

#define WIDTH            1000
#define HEIGHT           600
#define DEPTH            32
#define WINDOW_TITLE     "STICK MAN"

#define FPS              35
#define GRAVITY          3
#define Y_VELOCITY_STEP  -40

#define FRAME_STEP       0.4

/* Character */
#define MAN_WIDTH  80
#define MAN_HEIGHT 160

#define MAN_STEP   10
#define MAN_DASH   130


#define RUN_INDEX		8
#define REST_INDEX      6
#define HURTED_INDEX     4
#define JUMP_INDEX       7
#define ATTACK_INDEX     6
#define DEATH_INDEX     4
#define U_INDEX	  5
#define I_INDEX	  8
#define FALL_INDEX	  11
#define WIN_INDEX	  4
#define DASH_INDEX	  2
#define DEFENCE_INDEX	  4
#define W_J_INDEX	  7
#define S_U_INDEX	  12
#define S_J_INDEX		1




#define RUN_INDEX2		8
#define REST_INDEX2      4
#define HURTED_INDEX2     4
#define JUMP_INDEX2       8
#define ATTACK_INDEX2     5
#define DEATH_INDEX2     5
#define U_INDEX2	  7
#define I_INDEX2	  13
#define FALL_INDEX2	  10
#define WIN_INDEX2	  7
#define DASH_INDEX2	  2
#define DEFENCE_INDEX2	  3
#define W_J_INDEX2	  9
#define S_U_INDEX2	  16
#define S_J_INDEX2		11

#define MAN_BACK		0x00, 0x80,0x00
#define MAN_BACK2		0x73,0x39,0x84
#define BG_BACK			0xFF,0xFF,0xFF


#define NUMSTATES        15
#define NUMSKILLS		 2

#define ATTACK_DAMAGE    30
#define I_DAMAGE		5
#define S_J_DAMAGE		 30


#define GROUND_Y		 400

#define FACE_LEFT		-1
#define FACE_RIGHT		1


//image path
#define RUN_PATH "data//run.png"
#define REST_PATH "data//rest.png"
#define ATTACK_PATH "data//attack.png"
#define JUMP_PATH "data//jump.png"
#define HURTED_PATH "data//hurted.png"
#define DEATH_PATH "data//death.png"
#endif /* _CONFIG_H_ */
