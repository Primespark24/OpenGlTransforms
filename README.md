# Project 2 - Transformations
Whitworth University - CS-357 Computer Graphics  
Last edited: 3/5/2021 by Scott  

## Overview
We have been covering transforms, I want you to show me that you know how to apply them.

Be intentional as you approach this assignment. It is really easy to start slinging numbers, but that is not the point. Have an idea of what you want to do, then move forward.

You are welcome (and encouraged) to use provided code, both from me and from sb7 source code. Always be clear about your citations.

As this is a 300 level course, I expect adherence to style and appropriate and complete commenting.

As always: you can do this assignment in whatever Graphics Language you like, but you need to approach the theme of the original assignment if not doing it in OpenGL.

## Grade

| Portion             | Points Possible |
|---------------------|-----------------|
| Transformations     | 45              |
| Extras              | 15              |
| Proof               | 40              |

Please only upload original code and documentation! I don't want to see whole libraries uploaded or zip files unrelated to what you did. You should use a good `.gitignore` file, if you don't know what that is, let me know and I can show you.

## Part 1: Transformations

You are going to develop a graphics program that clearly demonstrates your mastery of transformations. I don't want to put too many fine details on the requirements, but I do want to specify the minimum requirements.

You need to clearly identify and demonstrate transforms that cover the following:
* Translation --
* Scale --
* Rotation --
* Reflection --
* Shearing --
* Inversion --
* Projection -- of 4
* Simple combinations of the above (more than just Translation + something else) --rotation, inversion, scale

(I would suggest tackling them in that order, Projection will be hard to capture until we get into perspective)

## Part 2: Extras

This is where I want a little creative expression. If you modify the code I gave out at the start of the transformations conversation and 'just' demo the transforms, that will get you 85%.

The rest needs to be made up by your expression of those transformations. This could take the form of an animation or notation. It could be user-interaction. It could be in what and/or how you are presenting.

Think of this as mandatory extra-credit. If this stresses you out: I can give you more concrete direction, but I want to keep it open to your interest. 

## Proof
Show and tell! Show off what you did!

You need to submit, with your above code, video documentation of your program working. This could be a gif, this could be a mpg4, this could be a youtube link. I don't care, you are in charge. 

## Suggested Resources:
* You might want to take a look at `sb7code/src/fontdemo`
* Glance at `Drawing Commands` in Chapter 7 (pg. 249). We will come back and talk more about Vertex Processing, but it is helpful to know how to display things.
* Along with ^^^ https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawElements.xhtml and https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
* You also might want to consider binding a key input to a specific transform (i.e. press 1 for rotation)