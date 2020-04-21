pipeline{
    agent any

    stages{
        stage ('Build') {
            steps{
                sh 'echo "Building..."'
                sh 'sudo Scripts/linux-build.sh'
                archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
            }
        }

        stage ('Test') {
            steps{
                sh 'echo "Running..."'
                sh 'sudo Scripts/linux-run.sh'
            }
        }
    }
}