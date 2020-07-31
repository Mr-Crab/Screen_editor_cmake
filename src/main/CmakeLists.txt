
#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB SRC_FILES "./*.cpp") 
#同理，查找当前文件夹中所有的头文件
FILE(GLOB HEAD_FILES "./*.h") 
#同理，查找当前文件夹中所有的ui文件
FILE(GLOB UI_FILES "./*.ui") 
 
#通过Ui文件生成对应的头文件，一定要添加
QT5_WRAP_UI(WRAP_FILES ${UI_FILES})
#将ui文件和生成文件整理在一个文件夹中，非必须
source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )

 
#添加资源文件	
#set(RCC_FILES ScreenEditor.qrc)
#QT5_ADD_RESOURCES(QRC_FILES ${RCC_FILES})

 
#创建工程文件
add_executable(${PROJECT_NAME}
	${SRC_FILES}
	${HEAD_FILES}
	${UI_FILES}
	ScreenEditor.qrc
)
 
#添加头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/thirdpart/include)

#添加依赖库目录
target_link_directories(${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/thirdpart/lib
)

#添加Qt5依赖项
target_link_libraries(${PROJECT_NAME} 
	Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Xml
	zip_x64
)
