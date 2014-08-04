
# Collect resources
file(GLOB_RECURSE RES . *.xsd *.xsl)
set(resources ${RES} PARENT_SCOPE)

message(${PROJECT_SOURCE_DIR}/${resourcedir})
message(${RES})
