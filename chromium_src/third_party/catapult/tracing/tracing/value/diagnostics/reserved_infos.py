QORAI_CHROME_VERSION = _Info('qoraiChromeVersion', 'GenericSet', str)
QORAI_TAG = _Info('qoraiTag', 'GenericSet', str)
QORAI_VARIATIONS_REVISIONS = _Info('qoraiVariationsRevisions', 'GenericSet',
                                   str)
QORAI_JOB_NAME = _Info('qoraiJobName', 'GenericSet', str)
QORAI_JOB_ID = _Info('qoraiJobId', 'GenericSet', str)
QORAI_TRACE_PATH = _Info('qoraiTracePath', 'GenericSet', str)

# Rewrite _CACHED_INFO_TYPES
_CACHED_INFO_TYPES = _CreateCachedInfoTypes()
