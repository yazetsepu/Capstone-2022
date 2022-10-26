namespace chamaecristasystem_api
{
    public interface EnvironmentalDataServiceInterface
    {
        //** getEnvData: Retrieves data from the database to siplay in the UI
        public IList<Object> getEnvData();

        //** getEnvDataByTime: Retrieves data from teh database that fits within the specified time stamps
        public IList<Object> getEnvDataByTime();

        //** postEnvData: Publish data from sensors to the database and run pictures through ML.NET
        public JsonContent postEnvData();

        //** updateEnvData: Update information featured in the environmental data
        public JsonContent updateEnvData();
    }
}
