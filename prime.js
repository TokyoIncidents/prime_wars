#!/usr/bin/env node

var prime = require('./build/Release/prime')
  , util = require('util')
  , sum = prime.sum(10000);

util.puts(sum);


