// rendered with POV-Ray
// http://povray.org/

#declare fin1 = finish { ambient .1 diffuse .8 reflection 0 phong .1 phong_size 8 }
#declare tex_silver = texture { pigment { color rgb <1, 1, 1> } finish { fin1 } }
#declare tex_red = texture { pigment { color rgb <1, 0, 0> } finish { fin1 } }

union {
  light_source {
      <-6, -6, -12>
      color rgb < .25, .25, .25>
  }
  light_source {
      <+6, -6, -12>
      color rgb < .25, .25, .25>
  }
  light_source {
      <-6, +6, -12>
      color rgb < .25, .25, .25>
  }
  light_source {
      <+6, +6, -12>
      color rgb < .25, .25, .25>
  }
  
  rotate <0,-clock*360,0>
}

camera {
  right 16*x/9
  up y
  location  <  20*sin(clock*2*pi),   0,  -20*cos(clock*2*pi)>
  look_at   <  0,   0,  0>
}

#declare eX = function(x, y) { sin(x*2*pi/y) }
#declare eY = function(x, y) { cos(x*2*pi/y) }

#declare oWrench = object {
  difference {
    union {
      // closed end sphere:
      sphere {
        0 1+1/3
        translate <0,-6,0>
      }
      
      // connecting thingee:
      intersection {
        box {
          <-1,-6,-1/4> <1,6,1/4>
        }
        cylinder {
          <0,-6,0> <0,6,0> 1
        }
      }
      
      // open end sphere:
      sphere {
        0 2-1/6
        translate <0,6,0>
      }      
    }
    
    // cuts at open end:
    union
    {
      cylinder {
        <0,1/6,-1>, <0,1/6,1>, 1
      }
      box {
        <-1,2+1/6,-1>, <1,1/6,1>
      }
      rotate <0,0,-11.25>    
      translate <0,6,0>
    }    
  
    // cuts at closed end:
    union {
      prism {
        -4, 4, 12,
        <eX(00,12),eY(00,12)>,
        <eX(01,12),eY(01,12)>,
        <eX(02,12),eY(02,12)>,
        <eX(03,12),eY(03,12)>,
        <eX(04,12),eY(04,12)>,
        <eX(05,12),eY(05,12)>,
        <eX(06,12),eY(06,12)>,
        <eX(07,12),eY(07,12)>,
        <eX(08,12),eY(08,12)>,
        <eX(09,12),eY(09,12)>,
        <eX(10,12),eY(10,12)>,
        <eX(11,12),eY(11,12)>
        rotate <90,0,0>
      }
      sphere {
        <0,0,1+1/3> 1+1/3
      }    
      sphere {
        <0,0,-1-1/3> 1+1/3
      }    
      translate <0,-6,0>
    }

  }   
    
}

intersection {
  union {
    object {
      oWrench
      rotate <0,0,45>
    }
    object {
      oWrench
      rotate <0,180,-45>
    }
  }
  
  // cut flat:
  box {
    <-10,-10,-1/2> <10,10,1/2>
  }
  
  texture { tex_silver }
}

cylinder {
  <0,0,-1/8>, <0,0,1/8> 9

  texture { tex_red }
}

difference {
  cylinder {
    <0,0,-1/6>, <0,0,1/6> 9+1/6
  }
  cylinder {
    <0,0,-1>, <0,0,1> 9-1/6
  }
  
  texture { tex_silver }
}
  
  