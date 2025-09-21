import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Float64

class HelloworldPublisher(Node):
    def __init__(self):
        super().__init__('python_publisher')
        self.helloworld_publisher = self.create_publisher(String, 'python', 10)
        self.double_publisher = self.create_publisher(Float64, 'double_topic', 10) 
        self.timer = self.create_timer(1, self.publish_helloworld_msg)
        self.double_timer = self.create_timer(1, self.publish_double) 
        self.count = 0
        self.mistake = 0.0

    def publish_helloworld_msg(self):
        msg = String()
        msg.data = 'im python: {0}'.format(self.count)
        self.helloworld_publisher.publish(msg)
        self.get_logger().info('Published message: {0}'.format(msg.data))
        
        self.count += 1
       
    def publish_double (self):
        msg1 = Float64()
        msg1.data = self.mistake                                                                       
        self.double_publisher.publish(msg1)                                                            
        self.get_logger().info('Published double: {0}'.format(msg1.data)) 
        self.mistake += 0.5

def main(args=None):
    rclpy.init(args=args)
    node = HelloworldPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Keyboard interrupt (SIGINT)')
    finally:
        node.destroy_node()
        rclpy.shutdown()
if __name__ == '__main__':
    main()