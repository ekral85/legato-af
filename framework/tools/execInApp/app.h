
#ifndef LEGATO_SRC_APP_INCLUDE_GUARD
#define LEGATO_SRC_APP_INCLUDE_GUARD


//--------------------------------------------------------------------------------------------------
/**
 * The application object reference.
 */
//--------------------------------------------------------------------------------------------------
typedef struct app_Ref* app_Ref_t;


//--------------------------------------------------------------------------------------------------
/**
 * Fault action.
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    APP_FAULT_ACTION_IGNORE = 0,        ///< Just ignore the fault.
    APP_FAULT_ACTION_RESTART_APP,       ///< The application should be restarted.
    APP_FAULT_ACTION_STOP_APP,          ///< The application should be stopped.
    APP_FAULT_ACTION_REBOOT             ///< The system should be rebooted.
}
app_FaultAction_t;


//--------------------------------------------------------------------------------------------------
/**
 * Application state.
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    APP_STATE_STOPPED,      ///< The application sandbox (for sandboxed apps) does not exist and no
                            ///  application processes are running.
    APP_STATE_RUNNING       ///< The application sandbox (for sandboxed apps) exists and atleast one
                            ///  application process is running.
}
app_State_t;


//--------------------------------------------------------------------------------------------------
/**
 * Process state.
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    APP_PROC_STATE_STOPPED, ///< The application process is not running.
    APP_PROC_STATE_RUNNING  ///< The application process is running.
}
app_ProcState_t;


//--------------------------------------------------------------------------------------------------
/**
 * Initialize the application system.
 */
//--------------------------------------------------------------------------------------------------
void app_Init
(
    void
);


//--------------------------------------------------------------------------------------------------
/**
 * Creates an application object.
 *
 * @note
 *      Only applications that have entries in the config tree can be created.
 *
 * @return
 *      A reference to the application object if success.
 *      NULL if there was an error.
 */
//--------------------------------------------------------------------------------------------------
app_Ref_t app_Create
(
    const char* cfgPathRootPtr          ///< [IN] The path in the config tree for this application.
);


//--------------------------------------------------------------------------------------------------
/**
 * Deletes an application.  The application must be stopped before it is deleted.
 *
 * @note If this function fails it will kill the calling process.
 */
//--------------------------------------------------------------------------------------------------
void app_Delete
(
    app_Ref_t appRef                    ///< [IN] Reference to the application to delete.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets an application's name.
 *
 * @return
 *      The application's name.
 */
//--------------------------------------------------------------------------------------------------
const char* app_GetName
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets an application's working directory.
 *
 * @return
 *      The application's sandbox path.
 */
//--------------------------------------------------------------------------------------------------
const char* app_GetWorkingDir
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets an application's UID.
 *
 * @return
 *      The application's UID.
 */
//--------------------------------------------------------------------------------------------------
uid_t app_GetUid
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets an application's GID.
 *
 * @return
 *      The application's GID.
 */
//--------------------------------------------------------------------------------------------------
gid_t app_GetGid
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


//--------------------------------------------------------------------------------------------------
/**
 * Check to see if the application is sandboxed or not.
 *
 * @return
 *      True if the app is sandboxed, false if not.
 */
//--------------------------------------------------------------------------------------------------
bool app_GetIsSandboxed
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets an application's configuration path.
 *
 * @return
 *      The application's configuration path.
 */
//--------------------------------------------------------------------------------------------------
const char* app_GetConfigPath
(
    app_Ref_t appRef                    ///< [IN] The application reference.
);


#endif  // LEGATO_SRC_APP_INCLUDE_GUARD
