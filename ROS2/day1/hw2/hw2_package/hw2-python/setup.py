from setuptools import find_packages, setup

package_name = 'hw2-python'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='bws',
    maintainer_email='bws@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [ 'myrclpy_node = hw2-python.myrclpy:main',
        'myrclpy1_node = hw2-python.myrclpy1:main'],
    },
)
