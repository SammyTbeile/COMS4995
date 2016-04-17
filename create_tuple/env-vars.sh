#!/bin/bash

# AWS MySQL C++ Connector

if [ $BASH_SOURCE == $0 ]
  then
  echo 'Aborting: script must be run in source mode'
  echo 'Please try again with the following command: . '$0
  exit
fi

# Parameters #
export DATABASE_CONNECTOR_URL='coms4995.ctwpugdpc3fd.us-east-1.rds.amazonaws.com'
export DATABASE_CONNECTOR_USERNAME='mysqluser'
export DATABASE_CONNECTOR_PASSWORD='bjarne_stroustrup'
export DATABASE_CONNECTOR_DATABASE='coms4995'
