pipeline{
    agent any

    stages{
        stage ('Build') {
            sh 'echo "Building..."'
            sh 'chmod +x scripts/linux-build.sh'
            sh 'scripts/linux-build.sh'
            archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
        }

        stage ('Test') {
            sh 'echo "Running..."'
            sh 'chmod +x scripts/linux-run.sh'
            sh 'scripts/linux-run.sh'
        }
    }
}