import rclpy
from rclpy.node import Node 
from std_msgs.msg import String,Float64
class HelloworldSubscriber(Node):

    def __init__(self) :
        super().__init__('python_subscriber')
        self.helloworld_subscriber = self.create_subscription(
            String, 
            'python',
            self.subscribe_topic_message,
            10
        )

        self.helloworld_subscriber1 = self.create_subscription(
            Float64, 
            'double_topic',
            self.subscribe_topic_double,
            10
        )
    def subscribe_topic_message(self,msg):
        self.get_logger().info('Received message: {0}'.format(msg.data))

    def subscribe_topic_double(self,msg1):
        self.get_logger().info('Received double: {0}'.format(msg1.data))

def main (args = None ) :
    rclpy.init(args=args)
    node = HelloworldSubscriber()
    try : 
        rclpy.spin (node)

    except KeyboardInterrupt :
        node.get_logger().info('Keyboard interrupt (SIGINT)')
    finally :
        node.destroy_node()
        rclpy.shutdown()
if __name__ =='__main__' :
    main()
