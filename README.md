  Blue Gravity Studios Task Overview
Utilizing the 3D Third-Person template from UE as a base, I tested some different ways to move
the character around, in a way that felt right and true to a skateboard, at least somewhat. After a
while of back and forth of testing and changing values I landed on something that felt decent, it
still didn’t feel as good as I thought it could be, but with limited time, I had to progress to the next
steps. The movement utilizes the CharacterMovement component of Unreal, so the Speeding
up and Slowing down are handled by it, with a multitude of values, like MaxVelocity, Friction,
Deceleration, etc. W to move forward, A/D to turn left or right and releasing Space causes the
player to jump
For the level, I loaded up a separate project with the City Park Env. Collection and built a small
park in there, and migrated it to the main project, to avoid unnecessary files being added.
Straight after that it would be the Scoring system, and I created a basic ScoreObject that let me
add it to the map, and then change both the mesh and the box collider to fit the needs of
whatever prop it was. When the player enters and leaves the box, the score gets increased by a
value defined in each prop for maximum configuration, and the UI will then be updated. This is
all kept in the GameMode, as the object sends the info to the GameMode, which then updates
the UI.
Adding in the animations was mostly smooth, but not finding a Push animation that was locked
in place, led me to manually edit the animation so all the frames are approximately on the same
spot, which does cause some jittering as it was not done completely perfect.
Overall I think I did a good job, not without its ups and downs, as getting the movement down
took quite some time, since it’s a more unusual type of movement and that definitely could still
be further improved. Other than that everything seemed straight-forward and simple.
I spent around 18 hours on the assessment, with the movement taking around 8/10 hours on
the movement, 4/5 hours spent on the level and creating the scoring system, and the remainder
on the animation and UI.
