{
  'target_defaults': {
    'default_configuration': 'Release',
    'configurations': {
      'Debug': {
        'defines':['DEBUG=1'],
        'cflags': ['-g', '-O0'],
      }, # Debug
      'Release': {
        'cflags': ['-O3'],
      }, # Release
    }, # configurations
  }, # target_defaults
}
