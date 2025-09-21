import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Float64
from turtlesim.srv import SetPen
from geometry_msgs.msg import Twist
import sys
import termios
import tty
import time

def get_key():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def Turtle_color_width(node, a, b, c, d):
        client = node.create_client(SetPen, '/turtle1/set_pen')
        req = SetPen.Request()
        req.r = a
        req.g = b
        req.b = c
        req.width = d
        req.off = 0
        client.call_async(req)

class TurtlePublisher(Node):
    def __init__(self):
        super().__init__('cmd_vel')
        self.TurtlePublisher = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        # self.Turtle_color_width_Publisher = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)

    

    def publish_move(self):
        while(1) :
            key = get_key()
            twist = Twist()
           
            if key == 'w':
                twist.linear.x = 2.0
            elif key == 's':
                twist.linear.x = -2.0
            elif key == 'a':
                twist.angular.z = 2.0
            elif key == 'd':
                twist.angular.z = -2.0
            elif key == '1' :
              Turtle_color_width(self,255, 0, 0,7)

              for i in range(4) :
                if(i==0) :
                 twist.linear.x = 2.0
         
                if(i==1) :
                 twist.linear.x = 0.0
                 twist.linear.y = 2.0
         
                if(i==2) :
                 twist.linear.x = -2.0
                 twist.linear.y = 0.0
                if(i==3) :
                 twist.linear.y = -2.0
                 twist.linear.x = 0.0
                self.TurtlePublisher.publish(twist) 
                time.sleep(0.5)
              continue

             

            elif key == '2' :
              Turtle_color_width(self,0, 0, 255,10)
              for i in range(5) :
                if(i==0) :
                 
                 twist.linear.x = 2.0
               
                if(i==1) :
                 twist.linear.x = 2.0
                 twist.linear.y = 2.0
             
                if(i==2) :
                 twist.linear.x = -2.0
                 twist.linear.y = 0.0
                
                if(i==3) :
                 twist.linear.x = -2.0

                if(i==4) :
                 twist.linear.x = 2.0
                 twist.linear.y = -2.0

                self.TurtlePublisher.publish(twist) 
                time.sleep(0.5)
              continue

                
            
            elif key == '3' :
               Turtle_color_width(self,0, 255, 0,17)
               
                
               twist.linear.x = 2.0
               twist.angular.z = 2.0
              
              
            
            self.TurtlePublisher.publish(twist)


def main(args=None):
    rclpy.init(args=args)
    node = TurtlePublisher()
    try : 
        node.publish_move()   
        
    except KeyboardInterrupt:
        node.get_logger().info('Keyboard interrupt (SIGINT)')
    finally:
        node.destroy_node()
        rclpy.shutdown()
if __name__ == '__main__':
    main()

