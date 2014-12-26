{
  'target_defaults': {
    'default_configuration': 'Release',
    'configurations': {
      'Debug': {
        'defines':['DEBUG=1'],
        'cflags': ['-g', '-O0', ' -std=c++11'],
      }, # Debug
      'Release': {
        'cflags': ['-O3', '-std=c++11'],
      }, # Release
    }, # configurations
  }, # target_defaults
}
